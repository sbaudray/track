Module.require("./IssueRoot.css");

module MarkIssueAsMutation = [%relay.mutation
  {|
mutation IssueRootMarkIssueAsMutation($input: MarkIssueAsInput!) {
  markIssueAs(input: $input) {
    issue {
      id
      status
    }
  }
}
|}
];

module Query = [%relay.query
  {|
    query IssueRootQuery($id: ID!) {
      issue(id: $id) {
          id
          title
          body
          status
          author {
            username
          }
        }
    }
|}
];
[@react.component]
let make = (~id) => {
  let queryData = Query.use(~variables={id: id}, ());
  let (mutate, _isMutating) = MarkIssueAsMutation.use();

  let markIssueAsClosed = _ => {
    let _ = mutate(~variables={
                     input: {
                       id,
                       status: `CLOSED,
                     },
                   }, ());
    ();
  };

  let markIssueAsOpen = _ => {
    let _ = mutate(~variables={
                     input: {
                       id,
                       status: `OPEN,
                     },
                   }, ());
    ();
  };

  <div>
    <CommonHeader />
    <main className="IssueRoot__main">
      {switch (queryData.issue) {
       | Some(issue) =>
         <div>
           <div className="IssueRoot__Issue_title">
             {React.string(issue.title)}
           </div>
           <div>
             {React.string(
                switch (issue.status) {
                | `OPEN => "Opened by " ++ issue.author.username
                | `CLOSED => "Closed by " ++ issue.author.username
                | _ => ""
                },
              )}
           </div>
           <div className="IssueRoot__Issue_body">
             {React.string(issue.body)}
           </div>
           {switch (issue.status) {
            | `OPEN =>
              <button onClick=markIssueAsClosed>
                {React.string("Mark as closed")}
              </button>
            | `CLOSED =>
              <button onClick=markIssueAsOpen>
                {React.string("Mark as opened")}
              </button>
            | _ => React.null
            }}
         </div>
       | None => <div> {React.string("fuck me")} </div>
       }}
    </main>
  </div>;
};
