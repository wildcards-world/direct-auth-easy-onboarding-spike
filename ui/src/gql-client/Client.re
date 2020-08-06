let graphqlEndpoint = "localhost:8080/v1/graphql";

let headers = {
  "eth-signature": "0xc46e2d4c2182ef506c9be3bec642878d8226bf69446bed045da63c6e415a2e0425d222e7e9db5dd42b32a337a9ca6055f7ca43c14ac0541c745ccd26a2cb44901b",
  "eth-address": "0xCB6F1a8fdcF0D8e16109ef629E85fB7a7b19876b",
};

let httpLink =
  ApolloClient.Link.HttpLink.make(
    ~uri=_ => "http://" ++ graphqlEndpoint,
    ~headers=Obj.magic(headers),
    (),
  );

let wsLink =
  ApolloClient.Link.WebSocketLink.(
    make(
      ~uri="ws://" ++ graphqlEndpoint,
      ~options=
        ClientOptions.make(
          ~connectionParams=
            ConnectionParams(Obj.magic({"headers": headers})),
          ~reconnect=true,
          (),
        ),
      (),
    )
  );

let terminatingLink =
  ApolloClient.Link.split(
    ~test=
      ({query}) => {
        let definition = ApolloClient.Utilities.getOperationDefinition(query);
        switch (definition) {
        | Some({kind, operation}) =>
          kind === "OperationDefinition" && operation === "subscription"
        | None => false
        };
      },
    ~whenTrue=wsLink,
    ~whenFalse=httpLink,
  );

let instance =
  ApolloClient.(
    make(
      ~cache=Cache.InMemoryCache.make(),
      ~connectToDevTools=true,
      ~defaultOptions=
        DefaultOptions.make(
          ~mutate=
            DefaultMutateOptions.make(
              ~awaitRefetchQueries=true,
              ~errorPolicy=All,
              (),
            ),
          ~query=
            DefaultQueryOptions.make(
              ~fetchPolicy=NetworkOnly,
              ~errorPolicy=All,
              (),
            ),
          ~watchQuery=
            DefaultWatchQueryOptions.make(
              ~fetchPolicy=NetworkOnly,
              ~errorPolicy=All,
              (),
            ),
          (),
        ),
      ~link=terminatingLink,
      (),
    )
  );
