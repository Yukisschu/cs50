### Three Voting Algorithms

---

- **Plurality vote**: every voter gets to vote for one candidate. At the end of the election, whichever candidate has the greatest number of votes is declared the winner of the election.

- **Runoof**: a ranked-choice system, voters can vote for more than one candidate. Instead of just voting for their top choice, they can rank the candidates in order of preference.
     In an instant runoff election, voters can rank as many candidates as they wish. If any candidate has a majority (more than 50%) of the first preference votes, that candidate is declared the winner of the election.

    If no candidate has more than 50% of the vote, then an “instant runoff” occurrs. The candidate who received the fewest number of votes is eliminated from the election, and anyone who originally chose that candidate as their first preference now has their second preference considered. 

    The process repeats: if no candidate has a majority of the votes, the last-place candidate is eliminated, and anyone who voted for them will instead vote for their next preference (who hasn’t already been eliminated). Once a candidate has a majority, that candidate is declared the winner.

- **Tideman**: a ranked-choice voting system, where voters can vote for more than one candidate. Instead of just voting for their top choice, they can rank the candidates in order of preference. The Tideman voting method (also known as “ranked pairs”)guarantees to produce the [_Condorcet winner_](https://en.wikipedia.org/wiki/Condorcet_winner_criterion#:~:text=The%20candidate%20who%20wins%20a,not%20exist%20in%20all%20cases.) of the election if one exists. Please check [this article](https://anhui-gui.com/posts/bitwise-operators/) for more comprehensive discussions regarding Tideman and [this repo](https://github.com/Yukisschu/tideman_algorithm) for the full version of the code.
