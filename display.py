import numpy as np
import matplotlib.pyplot as plt
import argparse


if __name__ == '__main__':

	parser = argparse.ArgumentParser()
	parser.add_argument('--path', default='result/lady2.txt', type=str, metavar='DIR', help='path to the reconstructed image text file')
	args = parser.parse_args()

	image = np.zeros((265, 265), dtype = np.float64)

	with open(args.path) as fp:
	    for row, line in enumerate(fp):
	        for column, pix in enumerate(line.split()):
	            image[row, column] = float(pix)
	            
	plt.imshow(image, cmap='gray',clim=(0,1))
	plt.xticks([])
	plt.yticks([])
	plt.show()