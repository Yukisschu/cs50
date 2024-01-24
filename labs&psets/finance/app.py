import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")



@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    if "login_in" in session:
        results = db.execute("""
            SELECT symbol, SUM(share) AS shares
            FROM stocks
            WHERE user_id = ?
            GROUP BY symbol""",
            session["user_id"]
        )

        prices = {}
        totals = {}
        total_value = 0
        for row in results:
            symbol = row["symbol"]
            shares = row["shares"]

            quote_data = lookup(symbol)
            price = quote_data["price"]
            prices[symbol] = price
            totals[symbol] = round(price * shares, 2)

            total_value += round(totals[symbol], 2)

        cash_result = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = round(cash_result[0]["cash"], 2)

        if total_value:
            TOTAL = total_value + cash
        else:
            TOTAL = cash

        return render_template("index.html", results = results, prices = prices, totals = totals, cash = cash, TOTAL = TOTAL)

    else:
        return redirect("/login")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        share = request.form.get("share")
        quote_data = lookup(symbol)
        session["price"] = quote_data["price"]

        if not symbol:
            return apology("must provide symbol", 403)

        if not share:
            return apology("must provide number of shares", 403)

        try:
            share = int(share)
        except ValueError:
            return apology("number of shares must be an integer", 403)

        if share <= 0:
            return apology("number of shares must be greater than 0", 403)

        if not quote_data:
            return apology("invalid symbol", 400)

        cost = share * session["price"]

        cash_result = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash_result[0]["cash"]

        if cost > cash:
            return apology("not enough cash", 400)

        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", cost, session["user_id"])

        db.execute("INSERT INTO stocks (user_id, symbol, share, price) VALUES (?, ?, ?, ?)", session["user_id"], symbol, share, session["price"])

        return redirect("/")

    else:
        return render_template("buy.html")




@app.route("/history")
@login_required
def history():
    history = db.execute("""
        SELECT symbol, share, timestamp
        FROM stocks
        WHERE user_id = ?""",
        session["user_id"]
    )

    prices = {}

    for row in history:
        symbol = row["symbol"]

        quote_data = lookup(symbol)
        price = quote_data["price"]
        prices[symbol] = price

    return render_template("history.html", history = history, prices = prices)




@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session['login_in'] = True

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote_data = lookup(symbol)
        if quote_data:
            session["symbol"] = quote_data["symbol"]
            session["price"] = quote_data["price"]

        if not symbol:
            return apology("must provide symbol", 403)

        if symbol not in session["symbol"]:
            return apology("invalid symbol", 400)

        return render_template("quoted.html")

    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        password_again = request.form.get("password_again")

        if not username:
            return apology("must provide username", 403)

        elif not password:
            return apology("must provide password", 403)

        elif not password_again:
            return apology("must repeat passowrd", 403)

        exist_user = db.execute(
            "SELECT * FROM users WHERE username = ?", username
        )

        if exist_user:
            return apology("username existed", 403)

        if not password == password_again:
            return apology("passwords do not match", 403)


        db.execute(
            "INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password)
        )

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])

@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        share = request.form.get("share")

        if not symbol:
            return apology("must provide symbol", 403)

        elif not share:
            return apology("must provide number of shares", 403)

        try:
            share = int(share)
        except ValueError:
            return apology("number of shares must be an integer", 403)

        if share <= 0:
            return apology("number of shares must be greater than 0", 403)

        exist_symbol = db.execute(
            "SELECT * FROM stocks WHERE symbol = ? AND user_id = ?", symbol, session["user_id"]
        )

        if not exist_symbol:
            return apology("symbol not found", 403)

        shares = db.execute(
            "SELECT SUM(share) AS total_shares FROM stocks WHERE symbol = ? AND user_id = ? GROUP BY symbol",
            symbol, session["user_id"]
        )[0]["total_shares"]

        if share > shares:
            return apology("not enough shares to sell", 403)

        quote_data = lookup(symbol)
        price = quote_data["price"]
        proceeds = share * price

        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?", proceeds, session["user_id"]
        )

        db.execute(
            "INSERT INTO stocks (user_id, symbol, share, price) VALUES (?, ?, ?, ?)",
            session["user_id"], symbol, -share, price
        )

        return redirect("/")

    else:
        return render_template("sell.html")
