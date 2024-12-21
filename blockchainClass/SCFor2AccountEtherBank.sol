//Riley Thompson
//826526487
pragma solidity ^ 0.4.26;
contract bank_m {
    address private AliceA;
    address private BobA;

    uint private AliceBalance;
    uint private BobBalance;
    uint private totalBalance;

    constructor(address Alice, address Bob) public {
        AliceA = Alice;
        BobA = Bob;
    }

    function deposit() public payable {
        if (msg.sender == AliceA) {
            AliceBalance += msg.value;
        } else if (msg.sender == BobA) {
            BobBalance += msg.value;
        }
        totalBalance += msg.value;
    }

    function withdraw(uint amount) public {
        require(msg.sender == AliceA || msg.sender == BobA, "Fail");
        if (msg.sender == AliceA) {
            require(AliceBalance >= amount, "Fail");
            AliceBalance -= amount;
            totalBalance -= amount;
            msg.sender.transfer(amount);
        } else if (msg.sender == BobA) {
            require(BobBalance >= amount, "Fail");
            BobBalance -= amount;
            totalBalance -= amount;
            msg.sender.transfer(amount);
        }
    }
}
