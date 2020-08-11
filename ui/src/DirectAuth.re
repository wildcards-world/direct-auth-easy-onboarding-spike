type t;

type constructorParams = {
  baseUrl: string,
  enableLogging: bool,
  proxyContractAddress: string, // details for test net
  network: string // details for test net
};

type initParams = {skipSw: bool};

type jwtParams = {
  domain: string,
  verifierIdField: string,
  connection: string,
  isVerifierIdCaseSensitive: bool,
};

type loginParams = {
  name: string,
  typeOfLogin: string,
  clientId: string,
  verifier: string,
  jwtParams: option(jwtParams),
};

type userInfo = {
  email: string,
  name: string,
  profileImage: string,
  verifier: string,
  verifierId: string,
  typeOfLogin: string,
  accessToken: string,
  idToken: string,
};

type loginObj = {
  publicAddress: string,
  privateKey: string,
  userInfo,
};

[@bs.module "@toruslabs/torus-direct-web-sdk"] [@bs.new]
external make: constructorParams => t = "default";

// let da =
//   make({
//     baseUrl: "http://localhost:3000/serviceworker/",
//     enableLogging: true,
//     proxyContractAddress: "0x4023d2a0D330bF11426B12C6144Cfb96B7fa6183", // details for test net
//     network: "ropsten" // details for test net
//   });

[@bs.send] external init: (t, initParams) => Js.Promise.t(unit) = "init";

let createTorusSdk = () => {
  let torusInstance =
    make({
      baseUrl: "http://localhost:3000/serviceworker/",
      enableLogging: true,
      proxyContractAddress: "0x4023d2a0D330bF11426B12C6144Cfb96B7fa6183", // details for test net
      network: "ropsten" // details for test net
    });

  torusInstance
  ->init({skipSw: false})
  ->Js.Promise.then_(() => {torusInstance->Js.Promise.resolve}, _);
};

[@bs.send]
external triggerLogin: (t, loginParams) => Js.Promise.t(loginObj) =
  "triggerLogin";

// let torusLogin: DirectAuth.t => Js.Promise.t(torusLoginObj) = [%raw
//   {|
//       (torusObj) => {
//         return torusObj.triggerLogin({
//           name: "Google",
//           typeOfLogin: "google",
//           clientId: "221898609709-obfn3p63741l5333093430j3qeiinaa8.apps.googleusercontent.com",
//           verifier: "google-lrc",
//         });
//       }
//     |}
// ];
