/**
 *  Program #2
 *  Creates Pokemon Cards
 *  CS160-7
 *  February 20, 2022
 *  @author  Riley Thompson
  */
public class TradingCard {

    protected String name;
    protected String image;

    /**
     * This is the constructor for the TradingCard class.
     * Instance field values are set in this class.
     * @param name
     * @param image
     */

    public TradingCard(String name, String image) {
        this.name = name;
        this.image = image;
    }

    /**
     * This gets the name of the card.
     * @return
     */
    public String getName() {
        return name;
    }

    /**
     * This gets the image of the card.
     * @return
     */
    public String getImg() {
        return image;
    }

    /**
     * This is the toStirng for the TradingCard class.
     */
    @Override
    public String toString() {
        return name;
    }
    
}
