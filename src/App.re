open User;

module Query = [%relay.query
  {|
  query AppMeQuery {
    me {
      user {
        id
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
  let user = User.ValueProvider.useValue();
  let userDispatch = User.DispatchProvider.useDispatch();

  let queryData = Query.use(~variables=(), ());

  React.useEffect1(
    () => {
      setFirstTime(_ => false);
      switch (queryData.me) {
      | Some({user: Some(user)}) =>
        userDispatch(
          Login({id: user.id, email: user.email, username: user.username}),
        )
      | _ => ignore()
      };

      Some(ignore);
    },
    [||],
  );

  let current_user =
    switch (firstTime, queryData.me) {
    | (true, Some({user: Some(user)})) =>
      Citizen({id: user.id, email: user.email, username: user.username})
    | (true, _) => Alien
    | (false, _) => user
    };

  switch (url.path, current_user) {
  | (_, Alien) => <LoginRoot />
  | ([], _) => <IssuesRoot />
  | (["issue", "new"], Citizen(user)) => <NewIssueRoot user />
  | (["issue", id], _) => <IssueRoot id />
  | (_, _) => <div> {React.string("Never gonna happen")} </div>
  };
};
