# Legendre Moments for Pattern Recognition and Reconstruction

Legendre moments are an image component used to limit the representation complexity by invoking Lengendre polynomials. Here we use this components to calculate images' similarities, and recognize the closest pattern for a test image from our database.

* The program is very memory efficient and fast, using C programming language, memory allocation and pointers destruction. 
* Legendre moments are stored in triangular allocated 2D arrays.
* the program is dynamic for different degrees of Legendre Coefficients and it is adaptable to larger data-bases.


### Prerequisites:

The only prerequesite need is a C compiler, go ahead and use your favorite (gcc, clang...). I will use ``gcc`` and ``make``.

#### Linux:

```
$ sudo apt install build-essential
```

#### Windows:

* Install the [MinGW instalation manager](https://osdn.net/projects/mingw/releases/)
* On All packages window, check `mingw32-gcc-*`and `ming32-make-*` 
* Put `C:/MinGW/bin` on your System path.

Run this command to make sure you have the compiler working correctly: `gcc --version`
### Installing:

`git clone https://github.com/ily-R/Form-recognition-.git`

### Testing:

After Installing run the following commands:

`cd Legendre-Moments-for-Pattern-Recognition-and-Reconstruction/src`
#### On Linux: 
`$ make` then `a.out`
#### On Windows:
`mingw32-make` then `a`

If you get some problems using make, just run the following command from the *src* directory:
`gcc main.c Reconnaissance_Formes.c myBmpGris.c` and then `a`

After building the the source files and running the executable file, you should see this:
<p align="center">
  <img src="readMe_data/Capture1.jpg"/>
</p>
