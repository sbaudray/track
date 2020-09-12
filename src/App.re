open User;

module Query = [%relay.query
  {|
  query AppMeQuery {
    me {
      user {
        username
        email
      }
      resultErrors {
        message
      }
    }
  }
|}
];

[@react.component]
let make = () => {
  let (firstTime, setFirstTime) = React.useState(() => true);
  let url = ReasonReactRouter.useUrl();
  let user = UserValueProvider.useValue();
  let userDispatch = UserDispatchProvider.useDispatch();

  let queryData = Query.use(~variables=(), ());

  React.useEffect1(
    () => {
      switch (queryData.me) {
      | Some({user: Some(user)}) =>
        setFirstTime(_ => true);
        userDispatch(Login({email: user.email, username: user.username}));
      | _ => ignore()
      };

      Some(ignore);
    },
    [|queryData.me|],
  );

  let current_user =
    switch (firstTime) {
    | true =>
      switch (queryData.me) {
      | Some({user: Some(user)}) =>
        Citizen({email: user.email, username: user.username})
      | _ => Alien
      }
    | _ => user
    };

  switch (url.path, current_user) {
  | (_, Alien) => <LoginRoot />
  | ([], _) => <IssuesRoot />
  | (["issue", id], _) => <IssueRoot id />
  | (_, _) => <div> {React.string("Never gonna happen")} </div>
  };
};
