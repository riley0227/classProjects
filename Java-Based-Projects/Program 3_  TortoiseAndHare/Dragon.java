/**  Dragon class
 *   inherits from abstract Racer class
 */

import java.awt.Graphics;
import java.awt.Color;
import java.util.Random;

/**
 *  Program #3
 *  A Dragon is a subclass of the Racer class and Dragon is a racer.
 *  CS160-3
 *  03/06/2022
 *  @author  Riley Thompson
 */
public class Dragon extends Racer
{
  private int speed;
	private Random rand;

  /** Default Constructor: calls Racer default constructor
   */
  public Dragon( )
  {
    super( );
    setRandAndSpeed();
  }

  /** Constructor
   *    @param rID   racer Id, passed to Racer constructor
   *    @param rX    x position, passed to Racer constructor
   *    @param rY    y position, passed to Racer constructor
   */
  public Dragon( String rID, int rX, int rY )
  {
    super( rID, rX, rY );
    setRandAndSpeed();
  }

  /** move:  calculates the new x position for the racer
   *   Dragon move characteristics: "Fly high and burn the competition(moves up and 
   *   down with each flap very fast)
   *   increment x by 7 if move < speed, and increments back 5 is move > speed. Then
   *   y is incremented by 1 if move < speed and no matter what decreases by 1.
   * 
   */
  public void move( )
  {
    int move =  rand.nextInt( 100 )  + 1;

    if ( move < speed )
    {
      setX( getX( ) + 7);
      setY(getY() + 1);
    }

    if ( move > speed )
    {
      setX( getX( ) - 5);
    }

    setY(getY() - 1);
    
  }

  /** draw: draws the Dragon at current (x, y) coordinate
   *       @param g   Graphics context
   */
  public void draw( Graphics g )
  {
    //creates start x and y positions
    int startX = getX( );
    int startY = getY( );
     
    g.setColor(Color.BLACK); // dark green

    // If the Dragon wins the race, moprph method is called, else the Dragon continues as
    // a normal Dragon.
    if(this.isWinner)
    {
      morph(g);
    }else{

      //body
      g.fillOval( startX - 15, startY - 5, 15, 25 );

      //head
      g.setColor(Color.GRAY); // Gray
      g.fillOval( startX - 15, startY - 15, 15, 15 );

      //wings
      g.fillArc(startX - 10, startY, 15, 30, 90, -90);
      g.fillArc(startX - 20, startY, 15, 30, 90, 90);

      //eyes
      g.setColor(Color.RED);  // Red
      g.fillOval( startX - 13, startY - 12,  5, 5 );
      g.fillOval( startX - 8, startY - 12, 5, 5 );

      //flame(mouth)
      g.setColor(Color.ORANGE);
      g.fillOval(startX - 11, startY - 6, 7, 5);

      //feet
      g.setColor(Color.GRAY);  // Gray
      g.fill3DRect( startX - 13, startY + 15,  5, 5, true );
      g.fill3DRect( startX - 8, startY + 15, 5, 5, true);
    }
  }

  /**
   * Sets rand and speed
   */
  private void setRandAndSpeed( ) 
  {
  // percentage of time (between 60 - 99%) that this Dragon moves each turn
    rand = new Random( );
    speed = rand.nextInt( 10 ) + 60;
  }
  /**
   * This is the morph method which makes the dragon into a large golden eggs showing that 
   * he is golden and that he has reached his golden egg/treasure.
   */
  @Override
  public void morph(Graphics g)
  {
    //Trophy/egg base
    g.setColor(Color.GRAY); //Gray
    g.fillRect(getX() - 300, getY() + 200, 200, 60);

    //Trophy/egg holder
    g.setColor(Color.BLUE); //Blue
    g.fillRect(getX() - 240, getY() + 200, 80, 24);

    //Trophy/egg
    g.setColor(Color.YELLOW); //Yellow
    g.fillOval(getX() - 285, getY() - 30, 170, 250);
  }
}