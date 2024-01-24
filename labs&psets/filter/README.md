### Image Filtering and Finding the Edge

---

- The function `grayscale` takes an image and turns it into a black-and-white version of the same image.
- The reflect function takes an image and reflects it horizontally.
- The blur function takes an image and turns it into a box-blurred version of the same image.
- The edges function takes an image and highlights the edges between objects, according to the [Sobel operator](https://en.wikipedia.org/wiki/Sobel_operator).


    In the Sobel filter algorithm, Gx and Gy values are computed for each of the three color channels (red, green, and blue) for every pixel in an image. This involves applying a 3x3 kernel to the surrounding pixels and multiplying them by corresponding values in the Gx and Gy kernels.

    - Gx is computed by multiplying pixels to the right by positive values and pixels to the left by negative values in the Gx kernel.
    - Gy is computed similarly for pixels above and below in the Gy direction. As a pixel can only have one value for each channel, the square root of Gx<sup>2</sup> + Gy<sup>2</sup> is calculated. The resulting value is rounded to the nearest integer and capped at 255 to match the integer range for color channels.
