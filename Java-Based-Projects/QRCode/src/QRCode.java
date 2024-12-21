/**
 *  Program #1
 *  Creates a QRCode
 *  CS160-7
 *  February 9, 2022
 *  @author  Riley Thompson
  */

import java.util.Random;

public class QRCode {
	
	private static int[][] grid;

/**
 * with given dimensions and seed, it creates a random
 * object with and a pattern array with the size of 
 * dimensions squared.  It creates the pattern with a for 
 * loop of just 0's and 1's. When the pattern in created 
 * the array with the pattern is returned.
 * @param dim
 * @param seed
 * @return pattern
 */
	public static int[] createPattern(int dim, int seed) {
		int[] pattern = new int[dim * dim];
		Random rand = new Random(seed);
		
		for(int i = 0; i < pattern.length; i++) {
			pattern[i] = rand.nextInt(2);
		}
		
		return pattern;
	}
	
	/**
	 * Sets the 2d grid to have columns with dim by rows dim.
	 * It then sets the grid with the numbers in the patter 
	 * given through the parameter.
	 * @param dim
	 * @param pattern
	 */
	public void setGrid(int dim, int[] pattern) {
		grid = new int[dim][dim];
		
		for(int i = 0; i < grid.length; i++) {
			for(int j = 0; j < grid[i].length; j++) {
				grid[j][i] = pattern[i + (j * dim)];
			}
		}
	}
	
	/**
	 * This is the getter method for the 2d array, grid.
	 * @return grid
	 */
	public int[][] getGrid() {
		return grid;
	}
	
	/**
	 * outputs the two-dimensional matrix passed as a 
	 * parameter row by row.
	 * @param matrix
	 */
	public void print(int[][] matrix) {
		for(int i = 0; i < matrix.length; i++) {
			for(int j = 0; j < matrix[i].length; j++) {
				System.out.print(matrix[i][j]);
			}
			System.out.println();
		}
	}
	
	/**
	 * outputs the one-dimensional pattern passed a a 
	 * parameter as a two-dimensional grid.
	 * @param pattern
	 */
	public void print(int[] pattern) {
		//have to make into grid printout
		int dim = (int)Math.sqrt(pattern.length);
		for(int i = 0; i < dim; i++) {
			for(int j = 0; j < dim; j++) {
				System.out.print(pattern[i + (j * dim)]);
			}
			System.out.println();
		}
	}
	
	/**
	 * outputs the class member grid as a two-dimensional 
	 * grid.
	 */
	public void print() {
		for(int i = 0; i < grid.length; i++) {
			for(int j = 0; j < grid[i].length; j++) {
				System.out.print(grid[i][j]);
			}
			System.out.println();
		}
	}
	
	/**
	 * Given the x position and y position of the upper 
	 * left of one Finder, it creates the entire finder,
	 * calling addSquares for all the sizes of squares in
	 * the finder.
	 * @param xPos
	 * @param yPos
	 */
	public void setFinder(int xPos, int yPos) {
		for(int i = 15; i > 1; i-=4) {
			if(i == 15) {
				addSquare(xPos, yPos, i, 1);
			}
			if(i == 11) {
				addSquare(xPos + 2, yPos + 2, i, 0);
			}
			if(i == 7) {
				addSquare(xPos + 4, yPos + 4, i, 2);
			}
			if(i == 3) {
				addSquare(xPos + 6, yPos + 6, i, 3);
			}
		}
	}
	
	/**
	 * adds all of the setFinder calls that are needed,
	 * one for each upper left corner of a finder.
	 */
	public void addFinders() {
		setFinder(0, 0);
		setFinder(0, grid[0].length - 15);
		setFinder(grid.length - 15, 0);
	}
	
	/**
	 * This adds a square to the given x and y position with
	 * a given border size and what number the square is.  This
	 * changes the value in the grid.
	 * @param startX
	 * @param startY
	 * @param borderSize
	 * @param number
	 */
	public void addSquare(int startX, int startY, int borderSize, int number) {
		for(int i = startX; i < borderSize + startX; i++) {
			for(int j = startY; j < borderSize + startY; j++) {
				grid[i][j] = number;
			}
		}
	}
	
	/**
	 * The main creates a qrc object of the class QRCode.  Then 
	 * creates the default values for seed and dim.Sets the 
	 * seed and dim to the default values.  Then creates a null 
	 * pattern array.  These are the setup values. 
	 * Then it checks to see if there are 2 arguments and if 
	 * there are, it sets the dim and seed to the values of the 
	 * arguments passed.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		
		QRCode qrc = new QRCode();
		final int DEFAULT_SEED = 160;
		final int DEFAULT_DIMENSION = 30;
		int seed = DEFAULT_SEED;
		int dim = DEFAULT_DIMENSION;
		int[] pattern = null;
		if(args.length == 2) {
			dim = Integer.parseInt(args[0]);
			seed = Integer.parseInt(args[1]);
		}
		pattern = createPattern(dim ,seed);
		qrc.setGrid(dim, pattern);
		qrc.addFinders();
		qrc.print();
		
	}
}
