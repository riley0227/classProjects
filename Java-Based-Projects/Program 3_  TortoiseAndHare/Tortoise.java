/**  Tortoise class
*    inherits from abstract Racer class
*/

import java.awt.Graphics;
import java.awt.Color;
import java.util.Random;

/**
 *  Program #3
 *  A Tortoise is a subclass of the Racer class and Tortoise is a racer.
 *  CS160-3
 *  03/06/2022
 *  @author  Riley Thompson
 */
public class Tortoise extends Racer
{
	private int speed;
	private Random rand;

  /** Default Constructor: calls Racer default constructor
  */
  public Tortoise( )
  {
    super( );
    setRandAndSpeed();
  }

  /** Constructor
  *    @param rID  racer Id, passed to Racer constructor
  *    @param rX    x position, passed to Racer constructor
  *    @param rY    y position, passed to Racer constructor
  */
    public Tortoise( String rID, int rX, int rY )
    {
      super( rID, rX, rY );
      setRandAndSpeed();
    }

  /** move:  calculates the new x position for the racer
  *   Tortoise move characteristics: "slow & steady wins the race"
  *      increment x by 1 most of the time
  */
  public void move( )
  {
    int move =  rand.nextInt( 100 )  + 1;
    if ( move < speed ){
      setX( getX( ) + 1 );
    }
  }

  /** draw: draws the Tortoise at current (x, y) coordinate
  *       @param g   Graphics context
  */
  public void draw( Graphics g )
  {
    int startX = getX( );
    int startY = getY( );
     
    //Sets color then morph2 is called if it wins
    g.setColor( new Color( 34, 139, 34 ) ); // dark green
    if(this.isWinner)
    {
      morph2(g);
    }

    //body
    g.fillOval( startX - 30, startY, 25, 15 );

    //If it wins, morph is called
    if(this.isWinner)
    {
      morph(g);
    }

    //head
    g.fillOval( startX - 10, startY + 5,  15, 10 );

    //flatten bottom
    g.clearRect( startX - 30, startY + 11, 35, 4 );

    //feet
    g.setColor( new Color( 34, 139, 34 ) );  // brown
    g.fillOval( startX - 27, startY + 10,  5, 5 );
    g.fillOval( startX - 13, startY + 10, 5, 5 );
  }
   
  private void setRandAndSpeed( ) 
  {
    // percentage of time (between 90 - 99%) that this tortoise moves each turn
    rand = new Random( );
    speed = rand.nextInt( 10 ) + 90;
  }
  

  //This is the morph method which makes two baby turtles that are behind the leading 
  //turtle that wons the race.
  @Override
  public void morph(Graphics g)
  {
    //creates turtle 1
    g.setColor( new Color( 34, 139, 34 ) ); // dark green

    //body
    g.fillOval( this.getX() - 100, this.getY(), 25, 15 );

    //head
    g.fillOval( this.getX() - 80, this.getY() + 5,  15, 10 );

    //flatten bottom
    g.clearRect( this.getX() - 100, this.getY() + 11, 35, 4 );

    //feet
    g.setColor( new Color( 34, 139, 34 ) );  // brown
    g.fillOval( this.getX() - 97, this.getY() + 10,  5, 5 );
    g.fillOval( this.getX() - 83, this.getY() + 10, 5, 5 );


    //Creates turtle 2
    g.setColor( new Color( 34, 139, 34 ) ); // dark green

    //body
    g.fillOval( this.getX() - 170, this.getY(), 25, 15 );

    //head
    g.fillOval( this.getX() - 150, this.getY() + 5,  15, 10 );

    //flatten bottom
    g.clearRect( this.getX() - 170, this.getY() + 11, 35, 4 );

    //feet
    g.setColor( new Color( 34, 139, 34 ) );  // brown
    g.fillOval( this.getX() - 167, this.getY() + 10,  5, 5 );
    g.fillOval( this.getX() - 153, this.getY() + 10, 5, 5 );
  }

  //This is the morph method which changes the body to Yellow 
  public void morph2(Graphics g)
  {
    g.setColor(Color.YELLOW);
  }
}