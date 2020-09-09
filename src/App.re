[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  Js.Console.log(url);

  switch (url.path) {
  | [] => <IssuesRoot />
  | ["issue", id] => <IssueRoot id />
  | _ => <IssuesRoot />
  };
};
