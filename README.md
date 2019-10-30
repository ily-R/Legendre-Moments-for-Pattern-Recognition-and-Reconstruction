# Legendre Moments for Pattern Recognition and Reconstruction

<p align="center">
  <img src="https://github.com/ily-R/Legendre-Moments-for-Pattern-Recognition-and-Reconstruction/blob/master/readMe_data/ress.JPG?raw=true" alt="capture reconstruction"/>
</p>

Legendre moments are an image component used to limit the representation complexity by invoking Lengendre polynomials. Here we use this components to calculate images' similarities, and recognize the closest pattern for a test image from our database.

* The program is very memory efficient and fast, using C programming language, memory allocation and pointers destruction. 
* Legendre moments are stored in triangular allocated 2D arrays.
* the program is dynamic for different degrees of Legendre Coefficients and it is adaptable to larger data-bases.


## Prerequisites:

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
## Installing:

`git clone https://github.com/ily-R/Legendre-Moments-for-Pattern-Recognition-and-Reconstruction.git`

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
  <img src="https://github.com/ily-R/Legendre-Moments-for-Pattern-Recognition-and-Reconstruction/blob/master/readMe_data/Capture1.JPG?raw=true" alt="capture reconstruction"/>
</p>

This will write result/.txt file containing the image reconstructed from the closet image in the database.
Now run the python file to display the results:
`python display.py --path result/lady2.txt`

## Inference: 
#### ALL the change will applied only to main.c

* If you want to get more precision, you can change the *ordre* varible to higher values and uncomment the following:
```
int main()
{

// if you want to recreate a database uncomment the block bellow

/**
    ecrireMlegendre("..\\database\\lady.bmp","..\\LegendreMoments\\lady.txt",ordre,2);
    ecrireMlegendre("..\\database\\barre.bmp","..\\LegendreMoments\\barre.txt",ordre,2);
    ecrireMlegendre("..\\database\\carre.bmp","..\\LegendreMoments\\carre.txt",ordre,1);
    ecrireMlegendre("..\\database\\dessin2.bmp","..\\LegendreMoments\\dessin2.txt",ordre,1);
    ecrireMlegendre("..\\database\\dessin3.bmp","..\\LegendreMoments\\dessin3.txt",ordre,1);
    ecrireMlegendre("..\\database\\snow2.bmp","..\\LegendreMoments\\snow2.txt",ordre,2);
    ecrireMlegendre("..\\database\\stop.bmp","..\\LegendreMoments\\stop.txt",ordre,1);
    ecrireMlegendre("..\\database\\cercle.bmp","..\\LegendreMoments\\cercle.txt",ordre,1);
**/
```

<p align="center">
  <img src="https://github.com/ily-R/Legendre-Moments-for-Pattern-Recognition-and-Reconstruction/blob/master/readMe_data/output%20image.jpg?raw=true" alt="capture reconstruction"/>
</p>

* if you want to test with another image change the following:
`comparaisonImages("testImages\\lady2.bmp","results\\lady2.txt",ordre,a,2,size,true);`

* Don't change beta, the normalization coeff. For better result, test with 1 or 2.

## Custom Data:

To update the database, but the your images of size (265, 265) into the file *database/* and add the following:
```
ecrireMlegendre("..\\database\\custom.bmp","..\\LegendreMoments\\custom.txt",ordre,1);
a[0]=lireMlegendre("..\\LegendreMoments\\custom.txt",ordre);
```
## Authors:
[ilyas Aroui](https://github.com/ily-R)

## Reference:

* [Image Analysis with Legendre Moment Descriptors](http://thescipub.com/PDF/jcssp.2015.127.136.pdf)
