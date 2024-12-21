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
