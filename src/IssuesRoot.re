Module.require("./IssuesRoot.css");

module Query = [%relay.query
  {|
  query IssuesRootQuery {
    issues {
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
let make = () => {
  let queryData = Query.use(~variables=(), ());

  <table className="IssuesRoot__table">
    <thead>
      <tr>
        <th> {React.string("Title")} </th>
        <th> {React.string("Status")} </th>
      </tr>
    </thead>
    <tbody>
      {switch (Belt.Array.length(queryData.issues)) {
       | 0 => <tr> <td colSpan=2> {React.string("No issues")} </td> </tr>
       | _ =>
         Belt.Array.map(queryData.issues, issue => {
           switch (issue) {
           | Some(issue) =>
             <tr key={issue.id}>
               <td>
                 <Link href={"issue/" ++ issue.id}>
                   {React.string(issue.title)}
                 </Link>
               </td>
               <td>
                 {React.string(
                    switch (issue.status) {
                    | `OPENED => "Opened"
                    | `CLOSED => "Closed"
                    | _ => ""
                    },
                  )}
               </td>
             </tr>
           | None => React.null
           }
         })
         ->React.array
       }}
    </tbody>
  </table>;
};
