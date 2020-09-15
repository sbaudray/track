let handleClick = (href, event) => {
  ReactEvent.Mouse.preventDefault(event);
  ReasonReactRouter.push(href);
};

[@react.component]
let make = (~href, ~className="", ~children) =>
  <a className href onClick={event => handleClick(href, event)}>
    children
  </a>;
