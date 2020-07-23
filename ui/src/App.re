type torusSdk;
type torusUserInfo = {
  email: string,
  name: string,
  profileImage: string,
  verifier: string,
  verifierId: string,
  typeOfLogin: string,
  accessToken: string,
  idToken: string,
};

type torusLoginObj = {
  publicAddress: string,
  privateKey: string,
  userInfo: torusUserInfo,
};

let getTorus: unit => Js.Promise.t(torusSdk) = [%raw
  {|
  () => {
    return require("./directauth.js").createTorusSdk();
  }
|}
];

module AuthPage = {
  [@react.component]
  let make = (~torusObj) => {
    Js.log(torusObj);
    let (yourEthAddress, setYourEthAddress) = React.useState(_ => None);

    let torusLogin: torusSdk => Js.Promise.t(torusLoginObj) = [%raw
      {|
      (torusObj) => {
        return torusObj.triggerLogin({
          name: "Google",
          typeOfLogin: "google",
          clientId: "221898609709-obfn3p63741l5333093430j3qeiinaa8.apps.googleusercontent.com",
          verifier: "google-lrc",
        });
      }
    |}
    ];

    let onClick = _ => {
      torusLogin(torusObj)
      ->Js.Promise.then_(
          loginObj => {
            setYourEthAddress(_ => Some(loginObj.publicAddress))
            ->Js.Promise.resolve
          },
          _,
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
       | Some(ethAddress) =>
         <>
           <h1> "You are logged in!"->React.string </h1>
           <p> ethAddress->React.string </p>
         </>
       }}
    </div>;
  };
};

[@react.component]
let make = () => {
  let (torusInstance, setTorusInstance) = React.useState(_ => None);
  React.useEffect0(() => {
    getTorus()
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
