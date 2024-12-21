var lastBlk = eth.blockNumber;
for (var i = 0; i < 5; i++) {
    var blk = eth.getBlock(lastBlk - i);
    console.log(JSON.stringify(blk)); 
}

var transactions = 0;

while (transactions < 2 && lastBlk > 0) {
    var block = eth.getBlock(lastBlk, true);
    if (block.transactions.length > 0) {
        for (var j = 0; j < block.transactions.length && transactions < 2; j++) {
            var tx = block.transactions[j];
            console.log(JSON.stringify(block.transactions[j]));
            transactions++;
        }
    }
    lastBlk--;
    if (transactions >= 2){
        break;
    }
}

