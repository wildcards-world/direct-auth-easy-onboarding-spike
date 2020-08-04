module LoggedInPage = {
  [@react.component]
  let make = (~privateKey, ~ethAddress) => {
    let testFunc = [%raw
      {|
      (privKey) => {
        const lib = require("./initPrivateKeyAandSignExample.js").exampleCode;
        lib(privKey);
      }
    |}
    ];
    testFunc(privateKey);
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
            name: "Google",
            typeOfLogin: "google",
            clientId: "221898609709-obfn3p63741l5333093430j3qeiinaa8.apps.googleusercontent.com",
            verifier: "google-lrc",
          },
        )
        ->Js.Promise.then_(
            loginObj => {
              setYourEthAddress(_ =>
                Some((loginObj.publicAddress, loginObj.privateKey))
              )
              ->Js.Promise.resolve
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
           <button onClick> "Google Login"->React.string </button>
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
  switch (torusInstance) {
  | None => <h1> "Loading"->React.string </h1>
  | Some(torusObj) =>
    // Js.log(torusInstance);
    <AuthPage torusObj />
  };
};
