Module.require("./LoginRoot.css");

module LoginMutation = [%relay.mutation
  {|
mutation LoginRootLoginMutation($input: LoginInput!) {
  login(input: $input) {
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
  let (mutate, _isMutating) = LoginMutation.use();
  let userDispatch = User.DispatchProvider.useDispatch();
  let (email, setEmail) = React.useState(() => "");
  let (password, setPassword) = React.useState(() => "");
  let (error, setError) = React.useState(() => None);

  let submitForm = (event: ReactEvent.Form.t) => {
    ReactEvent.Form.preventDefault(event);
    let _ =
      mutate(
        ~variables={
          input: {
            email,
            password,
          },
        },
        ~onCompleted=
          (response, _) => {
            switch (response.login) {
            | Some({user: Some(user)}) =>
              userDispatch(
                Login({
                  id: user.id,
                  email: user.email,
                  username: user.username,
                }),
              )
            | _ => setError(_ => Some("Unauthorized"))
            }
          },
        (),
      );
    ();
  };

  <div className="LoginRoot">
    <form onSubmit=submitForm>
      <label htmlFor="email"> {React.string("Email:")} </label>
      <input
        id="email"
        type_="text"
        value=email
        onChange={event => {
          let value = ReactEvent.Form.target(event)##value;
          setEmail(_ => value);
        }}
      />
      <label htmlFor="password"> {React.string("Password:")} </label>
      <input
        id="password"
        type_="password"
        value=password
        onChange={event => {
          let value = ReactEvent.Form.target(event)##value;
          setPassword(_ => value);
        }}
      />
      <button className="LoginRoot__submit">
        {React.string("Submit")}
      </button>
      {switch (error) {
       | Some(error) =>
         <span className="LoginRoot__error"> {React.string(error)} </span>
       | None => React.null
       }}
    </form>
  </div>;
};
