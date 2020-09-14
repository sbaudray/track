Module.require("./CommonHeader.css");

module LogoutMutation = [%relay.mutation
  {|
mutation CommonHeaderLogoutMutation {
  logout {
    ok
  }
}
|}
];

[@react.component]
let make = () => {
  let userDispatch = User.DispatchProvider.useDispatch();
  let (mutate, _isMutating) = LogoutMutation.use();
  let logout = _ => {
    let _ =
      mutate(
        ~variables=(),
        ~onCompleted=
          (_, _) => {
            userDispatch(Logout);
            Js.Console.log("hello");
          },
        (),
      );
    ();
  };

  <header className="CommonHeader">
    <span className="CommonHeader__Brand"> {React.string("Track")} </span>
    <button className="CommonHeader__Logout" onClick=logout>
      {React.string("Logout")}
    </button>
  </header>;
};
