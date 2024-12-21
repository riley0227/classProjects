/**
 *  Program #2
 *  Creates Pokemon Cards
 *  CS160-7
 *  February 20, 2022
 *  @author  Riley Thompson
  */
public class GamingCard extends TradingCard{

    protected String game;
    protected String category;

    /**
     * This is the constructor for the GamingCard class.
     * Calls the superclass with name and image.
     * Rest are initialized in this class.
     * @param name
     * @param image
     * @param category
     * @param game
     */
    public GamingCard(String name, String image, String category, String game) {
        super(name, image);
        this.category = category;
        this.game = game;
        this.name = name;
    }

    /**
     * This gets the game of the card
     * @return game
     */
    public String getGame() {
        return game;
    }

    /**
     * This gets the category of the card
     * @return category
     */
    public String getCategory() {
        return category;
    }

    /**
     * This is the toString method for the GamingCard class.
     */
    @Override
    public String toString() {
        return name + ": " + game + " character";
    }
    
}
