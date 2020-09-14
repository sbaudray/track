Module.require("./UserBadge.css");

[@react.component]
let make = (~username) =>
  <span className="UserBadge">
    {React.string(Js.String.charAt(0, username))}
  </span>;
