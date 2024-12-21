//Riley Thompson
//826526487
pragma solidity ^ 0.4.26;
contract findingMax {
  function findMax(int x, int y) public pure returns(int) {
    int maxNum;
    if(x > y) {
        maxNum = x;
    } else if (y > x) {
        maxNum = y;
    } else {
        // can be either as both are the same number, so either would be
        // the max
        maxNum = x;
    }

    return maxNum;
  }
} 
