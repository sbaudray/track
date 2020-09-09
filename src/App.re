module Query = [%relay.query
  {|
  query AppQuery {
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

  <table>
    <thead>
      <tr>
        <th> {React.string("Title")} </th>
        <th> {React.string("Status")} </th>
      </tr>
    </thead>
    {switch (Belt.Array.length(queryData.issues)) {
     | 0 => <tr> <td colSpan=2> {React.string("No issues")} </td> </tr>
     | _ =>
       Belt.Array.map(queryData.issues, issue => {
         switch (issue) {
         | Some(issue) =>
           <tr key={issue.id}>
             <td> {React.string(issue.title)} </td>
             <td> {React.string(issue.body)} </td>
           </tr>
         | None => React.null
         }
       })
       ->React.array
     }}
  </table>;
};
