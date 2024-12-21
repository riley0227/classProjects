/**  Bee class
 *   inherits from abstract Racer class
 */

import java.awt.Graphics;
import java.awt.Color;
import java.util.Random;

/**
 *  Program #3
 *  A Bee is a subclass of the Racer class and Bee is a racer.
 *  CS160-3
 *  03/06/2022
 *  @author  Riley Thompson
 */

public class Bee extends Racer
{
    //instance field
    private int speed;
	private Random rand;

    /** Default Constructor: calls Racer default constructor
     */
    public Bee( )
    {
        super( );
        setRandAndSpeed();
    }

    /** Constructor
     * 
     *    @param rID  racer Id, passed to Racer constructor
     *    @param rX    x position, passed to Racer constructor
     *    @param rY    y position, passed to Racer constructor
     */
    public Bee( String rID, int rX, int rY )
    {
        super( rID, rX, rY );
        setRandAndSpeed();
    }

    /** move:  calculates the new x position for the racer
     *   Bee move characteristics: "buzzes around and goes back and fourth eventaully gettting there"
     *   increment x by 3 if move < speed, and increments back 2 is move > speed.
     */
    @Override
    public void move( )
    {
        int move =  rand.nextInt(100)  + 1;
        if (move < speed)
        {
            setX(getX( ) + 3);
        }
        if (move > speed)
        {
            setX(getX( ) - 2);
        }
    }

    /** draw: draws the Bee at current (x, y) coordinate
     *       @param g   Graphics context
     */
    @Override
    public void draw(Graphics g)
    {
        //creates start x and y positions
        int startX = getX( );
        int startY = getY( );
        
        // If the Bee wins the race, moprph method is called, else the Bee continues 
        //as a normal bee.
        if(this.isWinner)
        {
            morph(g);
        }else{

            //body
            g.setColor(Color.YELLOW); // Yellow
            g.fillOval(startX - 30, startY, 25, 15);
      
            //head
            g.fillOval(startX - 12, startY - 5,  15, 15);

            //stinger
            g.setColor(Color.BLACK); //Black
            g.fillOval( startX - 31, startY + 3,  5, 5);

            //stripes
            g.fillRoundRect( startX - 25, startY, 4, 14, 5, 7);
            g.fillRoundRect( startX - 19, startY, 4, 15, 5, 7);
            g.fillRoundRect( startX - 13, startY + 1, 4, 13, 5, 7);

            //eye
            g.setColor(Color.CYAN); //Cyan
            g.fillOval(startX - 4, startY - 3,  4, 4);

            //Mouth
            g.setColor(Color.BLACK); //Black
            g.fillRect(startX - 4, startY + 5,  5, 1);

            //Wing
            g.setColor(Color.WHITE); //White
            g.fillOval(startX - 25, startY - 3,  14, 10);
        }
    }

    /**
     * Sets rand and speed
     */
    private void setRandAndSpeed( ) 
    {
        // percentage of time (between 70 - 99%) that this Bee moves forward each time
        rand = new Random( );
        speed = rand.nextInt( 10 ) + 70;
    }

    /**
     * This is the morph method which creates a bee removing the stripes and making the stinger
     * long and that the bee zooms with little red dots showing it stung in those spots.
     */
    @Override
    public void morph(Graphics g)
    {
        //body
        g.setColor(Color.YELLOW); //Yellow
        g.fillOval(getX() - 30, getY(), 25, 15);
      
        //head
        g.fillOval(getX() - 12, getY() - 5,  15, 15);

        //stinger expanded(it looks like it zooms across screen)
        g.setColor(Color.BLACK); //Black
        g.fillOval( getX() - 331, getY() + 3,  300, 5);
        
        //Adds red dots where the b "stung".
        g.setColor(Color.RED); //Red
        g.fillOval( getX() - 331, getY() + 3,  5, 5);
        g.fillOval( getX() - 340, getY() + 3,  5, 5);
        g.fillOval( getX() - 349, getY() + 3,  5, 5);
        g.fillOval( getX() - 358, getY() + 3,  5, 5);
        g.fillOval( getX() - 367, getY() + 3,  5, 5);
        g.fillOval( getX() - 376, getY() + 3,  5, 5);

        //eye
        g.setColor(Color.CYAN); //Cyan
        g.fillOval(getX() - 4, getY() - 3,  4, 4);

        //Mouth
        g.setColor(Color.BLACK); //Black
        g.fillRect(getX() - 4, getY() + 5,  5, 1);

        //Wing
        g.setColor(Color.WHITE); //White
        g.fillOval(getX() - 25, getY() - 3,  14, 10);
    }
}