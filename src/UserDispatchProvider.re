let initialValue: User.action => unit = _ => ignore();

let context = React.createContext(initialValue);

let useDispatch = () => React.useContext(context);

let make = React.Context.provider(context);
let makeProps = (~value, ~children, ()) => {
  "value": value,
  "children": children,
};
