/**
 *  Program #2
 *  Creates Pokemon Cards
 *  CS160-7
 *  February 20, 2022
 *  @author  Riley Thompson
  */
public class PokemonCard extends GamingCard{

    protected String type;
    protected int pokedex;
    protected String ability;

    /**
     * This is the constructor for the PokemonCard class.
     * Calls the superclass with name, image, cardType, and game.
     * Instance field values are set in this class.
     * @param name
     * @param image
     * @param cardType
     * @param game
     * @param type
     * @param pokedex
     * @param ability
     */
    public PokemonCard(String name, String image, String cardType, String game, String type, int pokedex, String ability) {
        super(name, image, cardType, game);
        this.type = type;
        this.pokedex = pokedex;
        this.ability = ability;
    }
    
    /**
     * This sets the type of pokemon
     * @param type
     */
    public void setType(String type){
        this.type = type;
    }

    /**
     * This gets the type of pokemon
     * @return type
     */
    public String getType() {
        return type;
    }

    /**
     * This sets the pokedex value of the pokemon
     * @param pokedex
     */
    public void setPokedex(int pokedex){
        this.pokedex = pokedex;
    }

    /**
     * This gets the pokedex value of the pokemon
     * @return pokedex
     */
    public int getPokedex() {
        return pokedex;
    }

    /**
     * This sets the ability of the pokemon
     * @param ability
     */
    public void setAbility(String ability){
        this.ability = ability;
    }

    /**
     * This gets the ability of the pokemon
     * @return ability
     */
    public String getAbility() {
        return ability;
    }

    /**
     * This is the to string for the PokemonCard class which calls
     * the superclass' toString method and adds onto it.
     */
    @Override
    public String toString() {
        return super.toString() + ", " + pokedex + ", a " + type + "-type with " + ability + " ability.";
    }
    
}
