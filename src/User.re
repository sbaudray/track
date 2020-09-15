type user = {
  id: string,
  username: string,
  email: string,
};

type t =
  | Alien
  | Citizen(user);

type action =
  | Login(user)
  | Logout;

module ValueProvider = {
  let context = React.createContext(Alien);

  let useValue = () => React.useContext(context);

  let make = React.Context.provider(context);
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
};

module DispatchProvider = {
  let context = React.createContext(ignore);

  let useDispatch = () => React.useContext(context);

  let make = React.Context.provider(context);
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
};

module Provider = {
  type state = {user: t};

  let reducer = (_state, action) => {
    switch (action) {
    | Login(user) => {user: Citizen(user)}
    | Logout => {user: Alien}
    };
  };

  [@react.component]
  let make = (~children) => {
    let (state, dispatch) = React.useReducer(reducer, {user: Alien});

    <ValueProvider value={state.user}>
      <DispatchProvider value=dispatch> children </DispatchProvider>
    </ValueProvider>;
  };
};
