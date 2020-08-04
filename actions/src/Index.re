open Serbet.Endpoint;
open Globals;

Dotenv.config();
[@bs.val] external port: string = "process.env.PORT";

Js.log2("port", port);

module Auth = {
  type authResponse = {
    [@bs.as "X-Hasura-User-Id"]
    xHasuraUserId: string,
    [@bs.as "X-Hasura-Role"]
    xHasuraRole: string,
    [@bs.as "X-Hasura-Is-Owner"]
    xHasuraIsOwner: string,
    [@bs.as "X-Hasura-Custom"]
    xHasuraCustom: string,
  };
  type headers = {
    [@bs.as "eth-signature"]
    ethSignature: string,
    [@bs.as "eth-address"]
    ethAddress: string,
  };
  type authInput = {headers};

  let validateEthSignature = (ethSignature, ethAddress) => {
    true;
  };

  // NOT typesafe, but there is a level of trust from hasura :)
  let getAuthHeaders: Express.Request.t => authInput = [%raw
    {|(req) => req.body|}
  ];

  let authResponseToJson: authResponse => Js.Json.t = Obj.magic;

  let endpoint =
    Serbet.endpoint({
      verb: POST,
      path: "/auth",
      handler: req => {
        let {headers: {ethSignature, ethAddress}} = getAuthHeaders(req.req);

        if (validateEthSignature(ethSignature, ethAddress)) {
          {
            xHasuraUserId: "something",
            xHasuraRole: "something",
            xHasuraIsOwner: "something",
            xHasuraCustom: "something",
          }
          ->authResponseToJson
          ->OkJson
          ->async;
        } else {
          Unauthorized("")->async;
        };
      },
    });
};

let app =
  Serbet.application(
    ~port=port->int_of_string_opt |||| 9898,
    [Auth.endpoint],
  );
