/** Hare class
 *   inherits from abstract Racer class
 */

import java.awt.Graphics;
import java.awt.Color;
import java.util.Random;

/**
 *  Program #3
 *  A Hare is a subclass of the Racer class and Hare is a racer.
 *  CS160-3
 *  03/06/2022
 *  @author  Riley Thompson
 */
public class Hare extends Racer
{
  /** Default Constructor: calls Racer default constructor
   */
  public Hare( )
  {
    super( );
  }

  /** Constructor
   *    @param rID   racer Id, passed to Racer constructor
   *    @param rX    x position, passed to Racer constructor
   *    @param rY    y position, passed to Racer constructor
   */

  public Hare( String rID, int rX, int rY )
  {
    super( rID, rX, rY );
  }

  /** move:  calculates the new x position for the racer
   *   Hare move characteristics:  30% of the time, Hare jumps 5 pixels
   *                               70% of the time, Hare sleeps (no move)
   *   generates random number between 1 & 10
   *          for 1 - 7,  no change to x position
   *          for 8 - 10, x position is incremented by 5
   */
   
  public void move( )
  {
    Random rand = new Random( );
    int move =  rand.nextInt( 10 ) + 1 ;

    if ( getX( ) < 100 )
    {
      if ( move > 7 )
      {
        setX( getX( ) + 5 );
      }
    }else{
      if ( move > 7 )
      {
        setX( getX( ) + 5 );
      }
    }
  }

  /** draw: draws the Hare at current (x, y) coordinate
   *   @param g   Graphics context
   */
  public void draw( Graphics g )
  {
    int startY = getY( );
    int startX = getX( );

    //calls morph2 method if it wins.
    if(this.isWinner)
    {
      morph2(g);
    }
    //tail and if it wins, calls morph method.
    g.setColor( Color.LIGHT_GRAY );
    if(this.isWinner)
    {
      morph(g);
    }
    g.fillOval( startX - 37, startY + 8,  12, 12 );

    //body and if it wins, calls morph3 method.
    g.setColor( Color.GRAY );
    if(this.isWinner)
    {
      morph3(g);
    }
    g.fillOval( startX - 30, startY,  20,  20 );

    //head
    g.fillOval( startX - 13, startY + 2, 13, 8 );
    g.fillOval( startX - 13, startY - 8, 8, 28 );

    //flatten bottom
    g.clearRect( startX - 37, startY + 15, 32, 5 );
  }

  @Override
  //Morph method which changes tail to green
  public void morph(Graphics g){
    g.setColor(Color.GREEN); //Green
  }
  
  //Morph method which makes a carrot for the hare
  public void morph2(Graphics g){
    g.setColor(Color.ORANGE); //Orange
    g.fillOval(this.getX(), this.getY(), 5, 15);
    g.setColor(Color.GREEN); //Green
    g.fillOval(this.getX(), this.getY(), 5, 5);
  }

  //Morph method which makes the body Magenta
  public void morph3(Graphics g){
    g.setColor(Color.MAGENTA); //Magenta
  }
}