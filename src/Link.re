let handleClick = (href, event) => {
  ReactEvent.Mouse.preventDefault(event);
  ReasonReactRouter.push(href);
};

[@react.component]
let make = (~href, ~children) =>
  <a href onClick={event => handleClick(href, event)}> children </a>;
