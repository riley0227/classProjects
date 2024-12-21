// SPDX-License-Identifier: BADD Labs
// Riley Thompson 826526487
pragma solidity >=0.7.0 <0.9.0; 
contract BaddToken {  
  uint _totalSupply = 0; string _symbol;  
  mapping(address => uint) balances;  
  mapping(address => mapping(address => uint256)) private allowances;

  constructor(string memory symbol, uint256 initialSupply) {
    _symbol = symbol;
    _totalSupply = initialSupply;
    balances[msg.sender] = _totalSupply;  
  }
  
  function transfer(address receiver, uint amount) public returns (bool) {    
    require(amount <= balances[msg.sender]);        
    balances[msg.sender] = balances[msg.sender] - amount;    
    balances[receiver] = balances[receiver] + amount;    
    return true;  
  }

  function balanceOf(address account) public view returns(uint256){
    return balances[account];
  }

  function approve(address spender, uint256 amount) external returns (bool) {
    // set the allowance of spender
    allowances[msg.sender][spender] = amount;
    // true returned - show exucted succesfully
    return true;
  }

  function allowance(address owner, address spender) external view returns (uint256) {
    // return the amount of tokens allowed to be spent by the spender by a particular owner
    return allowances[owner][spender];
  }

  function transferFrom(address sendingAccount, address recievingAccount, uint256 amount) external returns (bool) {
    // makes sure enough tokens to transfer
    require(amount <= balances[sendingAccount], "balance not enough");
    // makes sure the sender is able to tranfer that amount
    require(amount <= allowances[sendingAccount][msg.sender], "allowance not enough");

    // increase balance of the reciving account by the specified amount
    balances[recievingAccount] += amount;
    // decrease balance of the spender by the specified amount
    balances[sendingAccount] -= amount;
    // the allowance is reduced by the specified amount for the msg.sender
    allowances[sendingAccount][msg.sender] -= amount;

    // true returned - show exucted succesfully
    return true;
  }
}

contract AMMPool {
  BaddToken tokenX;
  BaddToken tokenY;
  // _tokenX and _tokenY are contract-addresses running BaddToken SC
  constructor(address _tokenX, address _tokenY){
    tokenX = BaddToken(_tokenX); tokenY = BaddToken(_tokenY);
  }

  function swapXY(uint amountX) public payable {
    // need to calculate y for ratio stated(dy/dx = 2), amount y for x
    uint256 amountY = amountX * 2;
    // sees if enough of tokeny
    bool hasBalanceY = tokenY.balanceOf(address(this)) >= amountY;
    // sees if msg.sender gave enough allowance to pool to spend tokenX
    bool hasAllowanceX = tokenX.allowance(msg.sender, address(this)) >= amountX;

    // below check to see if the above statements are true or false and requires them to be true, so the pool has
    // enough token y and allowance is enough
    require(hasBalanceY, "not enough balance of TokenY in the pool");
    require(hasAllowanceX, "not enough allowance for TokenX");

    // send specified amount of tokenx(amountX) from msg.sender to the pool
    tokenX.transferFrom(msg.sender, address(this), amountX);

    // send specified amount of from pool to message sender
    tokenY.transfer(msg.sender, amountY);
  } 
}
