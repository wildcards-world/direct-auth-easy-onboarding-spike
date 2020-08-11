// var recover_2 = web3.eth.accounts.recover(message, signature);
type t;

[@bs.module] [@bs.new] external make: unit => t = "web3";
[@bs.module] [@bs.new] external makeWithProvider: string => t = "web3";

[@bs.send] [@bs.scope ("eth", "accounts")]
external ecRecover: (t, string, string) => string = "recover";
