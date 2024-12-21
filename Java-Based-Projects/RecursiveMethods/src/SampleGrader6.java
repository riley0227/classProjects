public class SampleGrader6 {
    public static void main(String[] args) {
        RecursiveMethods p6 = new RecursiveMethods();
        
        int partI = p6.byLeapsAndBounds(7);
        System.out.println("Part I answer: " + partI); //should print Part I answer: 3

        int partII = p6.subCount("rtryrttyryrtrt", "rt");
        System.out.println("Part II answer: " + partII); //should print Part II answer: 4

        int[]sampleArr = {1,2,3,5,6,8,13};
        int partIII = p6.binarySearch(sampleArr,57,0,sampleArr.length-1); 
        System.out.println("Part III answer: " + partIII); //should print Part III answer: 2
    }
}