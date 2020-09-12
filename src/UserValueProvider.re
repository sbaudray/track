let initialValue: User.t = Alien;

let context = React.createContext(initialValue);

let useValue = () => React.useContext(context);

let make = React.Context.provider(context);
let makeProps = (~value, ~children, ()) => {
  "value": value,
  "children": children,
};
