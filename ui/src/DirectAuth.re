type t;

type constructorParams = {
  baseUrl: string,
  enableLogging: bool,
  proxyContractAddress: option(string), // details for test net
  network: option(string) // details for test net
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
      proxyContractAddress: None,
      network: None,
      // proxyContractAddress:
      //   Some("0x4023d2a0D330bF11426B12C6144Cfb96B7fa6183"), // details for test net
      // network: Some("ropsten") // details for test net
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
/**
I'm now getting basically the same error as I got for testnet for mainnet (see image).

The login object that gets printed to console.
```
{
  "instanceParams": {
    "instanceId": "sZTyZg5oKorqXjdItoJBxf6S00LgMf",
    "verifier": "wildcards-auth0-passwordless",
    "redirectToOpener": false,
  },
  "hashParams": {
    "access_token": "L4B9VJIgbzwNoBEstCIjsjsUaNl7i-dk",
    "scope": "openid%20profile%20email",
    "expires_in": "7200",
    "token_type": "Bearer",
    "state": "eyJpbnN0YW5jZUlkIjoic1pUeVpnNW9Lb3JxWGpkSXRvSkJ4ZjZTMDBMZ01mIiwidmVyaWZpZXIiOiJ3aWxkY2FyZHMtYXV0aDAtcGFzc3dvcmRsZXNzIiwicmVkaXJlY3RUb09wZW5lciI6ZmFsc2V9",
    "id_token": "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCIsImtpZCI6Ik56ZEdNa1F5UWtNNU1rVXhSVU5ETkVFelJESkdSRGhDTWpFeE1UaEdPRFF4TmtFNE16WTRPQSJ9.eyJuaWNrbmFtZSI6Imphc29uIiwibmFtZSI6Imphc29uQHdpbGRjYXJkcy53b3JsZCIsInBpY3R1cmUiOiJodHRwczovL3MuZ3JhdmF0YXIuY29tL2F2YXRhci9kNTUxNjcxZjBjYTczMmJhOWFiZDFiNThlZTJjNWE2MT9zPTQ4MCZyPXBnJmQ9aHR0cHMlM0ElMkYlMkZjZG4uYXV0aDAuY29tJTJGYXZhdGFycyUyRmphLnBuZyIsInVwZGF0ZWRfYXQiOiIyMDIwLTA4LTE0VDA4OjUwOjIxLjAzNVoiLCJlbWFpbCI6Imphc29uQHdpbGRjYXJkcy53b3JsZCIsImVtYWlsX3ZlcmlmaWVkIjp0cnVlLCJpc3MiOiJodHRwczovL2phc29vbnMuZXUuYXV0aDAuY29tLyIsInN1YiI6ImVtYWlsfDVmMWMxZGQyNzZjODUzNjcyOGNhMTI4ZSIsImF1ZCI6IlZvbEhxaXIzRkx6R2p2dGd0Z0pKMUgyNXZIR2o5dU1xIiwiaWF0IjoxNTk3Mzk1MDIxLCJleHAiOjE1OTc0MzEwMjEsImF1dGhfdGltZSI6MTU5NzM5NTAyMSwiYXRfaGFzaCI6InJQSGdoQnN4cFRlRVUwRGZnYVhMY0EiLCJub25jZSI6InNaVHlaZzVvS29ycVhqZEl0b0pCeGY2UzAwTGdNZiJ9.XMxk-u2ArHnEUITekiiHImg_sgGnk2YO1g0CfdMkBUeVMj-UQZVNV5QglR8bUp5Du4jEvKjTUQRZvimpqMnmnXYGFjU3mhe5cWUSM1SrDWmmZmLTPnrMqLTJCRYBTF9E-Utn6BnIpoQ-bPzXdDOC0GMES5SL6nM40Y2NEbBOWZx6ktQoiJhiADeMJDd3U5o5qEoyiFi4SBgd54Pt__bNKpTanUaaju6Z2IqMdIxo9dCG_CsGOStGUwRi6h3vAqdHDZUF7phJF1gwOh7mGIQWgcUwVblB6HiQxhScW-PT95uPHdkFkWBrtmf1aZc_sG8klRcSEeYgcwI-d-FE7IPhAg",
  },
  "queryParams": {},
};
```

Initialize directauth code:
```
function createTorusSdk(param) {
  var torusInstance = new TorusDirectWebSdk.default({
    baseUrl: "http://localhost:3000/serviceworker/",
    enableLogging: true,
    proxyContractAddress: undefined,
    network: undefined,
  });
  var __x = torusInstance.init({
    skipSw: false,
  });
  return __x.then(function (param) {
    return Promise.resolve(torusInstance);
  });
}
```

And code that triggers the login:
```
  var onClick = function (param) {
    var __x = torusObj.triggerLogin({
      name: "Hosted Email Passwordless",
      typeOfLogin: "jwt",
      clientId: "VolHqir3FLzGjvtgtgJJ1H25vHGj9uMq",
      verifier: "wildcards-auth0-passwordless",
      jwtParams: {
        domain: "https://jasoons.eu.auth0.com",
        verifierIdField: "name",
        connection: "",
        isVerifierIdCaseSensitive: false,
      },
    });
    __x.then(function (loginObj) {
      console.log("THE LOGIN OBJECT", loginObj);
      return Promise.resolve(
        Curry._1(setYourEthAddress, function (param) {
          return [loginObj.publicAddress, loginObj.privateKey];
        })
      );
    });
  };
```

(it is autogenerated code)
 */;
