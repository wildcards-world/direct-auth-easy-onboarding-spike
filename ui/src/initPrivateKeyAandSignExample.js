var PrivateKeyProvider = require("truffle-privatekey-provider");
const Web3 = require("web3");

// take in private key
// create an ethereum privider with the private key (and infura)
export const exampleCode = async (privateKey, publicKey) => {
  var provider = new PrivateKeyProvider(
    privateKey,
    "wss://mainnet.infura.io/ws/v3/e8fe0574d5124106b82126c48b689bd9"
  );

  let web3 = new Web3(provider);

  web3.eth.getAccounts(console.log);

  const message = "signin-string-for-wildcards:" + publicKey;

  const signature = await web3.eth.personal.sign(message, publicKey);

  console.log(signature);

  // var recover_2 = web3.eth.accounts.recover(message, signature);
  // console.log("recover 2 :", recover_2);
  return signature;
};
