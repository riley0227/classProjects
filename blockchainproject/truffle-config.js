module.exports = {
  networks: {
    development: {
      host: "127.0.0.1",
      port: 7545, 
      network_id: "*"
    }
  },
  solc: {
    optimizer: {
      enabled: true,
      runs: 200
    },

    version: "^0.5.16" 

  }
}
