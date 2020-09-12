open User;

type state = {user: User.t};

let reducer = (_state, action) => {
  switch (action) {
  | Login(user) => {user: Citizen(user)}
  | Logout => {user: Alien}
  };
};

[@react.component]
let make = (~children) => {
  let (state, dispatch) = React.useReducer(reducer, {user: Alien});

  <UserValueProvider value={state.user}>
    <UserDispatchProvider value=dispatch> children </UserDispatchProvider>
  </UserValueProvider>;
};
