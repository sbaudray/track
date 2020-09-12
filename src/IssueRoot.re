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

  switch (queryData.issue) {
  | Some(issue) =>
    <div>
      <div> {React.string(issue.title)} </div>
      <div> {React.string(issue.author.username)} </div>
      <div> {React.string(issue.body)} </div>
      <div>
        {React.string(
           switch (issue.status) {
           | `OPENED => "Opened"
           | `CLOSED => "Closed"
           | _ => ""
           },
         )}
      </div>
      <button onClick=markIssueAsClosed>
        {React.string("Mark as closed")}
      </button>
    </div>
  | None => <div> {React.string("fuck me")} </div>
  };
};
