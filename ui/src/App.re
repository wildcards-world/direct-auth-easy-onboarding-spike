module LoggedInPage = {
  [@react.component]
  let make = (~privateKey, ~ethAddress) => {
    let testFunc = [%raw
      {|
      (privKey, publicKey) => {
        const lib = require("./initPrivateKeyAandSignExample.js").exampleCode;
        lib(privKey, publicKey);
      }
    |}
    ];
    testFunc(privateKey, ethAddress);
    <>
      <h1> "You are logged in!"->React.string </h1>
      <p> ethAddress->React.string </p>
      <p> privateKey->React.string </p>
    </>;
  };
};

module AuthPage = {
  [@react.component]
  let make = (~torusObj) => {
    let (yourEthAddress, setYourEthAddress) = React.useState(_ => None);

    let onClick = _ => {
      DirectAuth.(
        triggerLogin(
          torusObj,
          {
            name: "Hosted Email Passwordless",
            typeOfLogin: "jwt",
            // clientId: "VolHqir3FLzGjvtgtgJJ1H25vHGj9uMq",
            clientId: "P7PJuBCXIHP41lcyty0NEb7Lgf7Zme8Q",
            // clientId: "lXlMA51Cpf63nU7IOA4kbCYR7E0a3cIB",
            verifier: "torus-auth0-passwordless",
            jwtParams:
              Some({
                // domain: "https://jasoons.eu.auth0.com",
                domain: "https://torus-test.auth0.com",
                // domain: "https://dev-q6kst0rx.eu.auth0.com",
                verifierIdField: "name",
                connection: "",
                isVerifierIdCaseSensitive: false,
              }),
          },
          // {
          //   name: "Google",
          //   typeOfLogin: "google",
          //   clientId: "221898609709-obfn3p63741l5333093430j3qeiinaa8.apps.googleusercontent.com",
          //   verifier: "google-lrc",
          // },
        )
        ->Js.Promise.then_(
            loginObj => {
              Js.log2("THE LOGIN OBJECT", loginObj);
              setYourEthAddress(_ =>
                Some((loginObj.publicAddress, loginObj.privateKey))
              )
              ->Js.Promise.resolve;
            },
            _,
          )
      )
      ->ignore;
    };

    <div>
      {switch (yourEthAddress) {
       | None =>
         <>
           <h1> "Login With DirectAuth"->React.string </h1>
           <button onClick> "Passwordless Login"->React.string </button>
         </>
       | Some((ethAddress, privateKey)) =>
         <LoggedInPage privateKey ethAddress />
       }}
    </div>;
  };
};

[@react.component]
let make = () => {
  let (torusInstance, setTorusInstance) = React.useState(_ => None);
  React.useEffect0(() => {
    DirectAuth.createTorusSdk()
    ->Js.Promise.then_(
        torusInstance => {
          setTorusInstance(_ => Some(torusInstance))->Js.Promise.resolve
        },
        _,
      )
    ->ignore;
    None;
  });
  <ApolloClient.React.ApolloProvider client=Client.instance>
    {switch (torusInstance) {
     | None => <h1> "Loading"->React.string </h1>
     | Some(torusObj) => <AuthPage torusObj />
     }}
  </ApolloClient.React.ApolloProvider>;
};
