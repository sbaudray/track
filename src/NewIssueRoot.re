module NewIssueMutation = [%relay.mutation
  {|
  mutation NewIssueRootCreateIssueMutation($input: CreateIssueInput!) {
    createIssue(input: $input) {
      issue {
        id
        title
        body
        author {
          username
        }
      }
    }
  }
|}
];

[@react.component]
let make = (~user: User.user) => {
  let (mutate, _isMutating) = NewIssueMutation.use();

  let (title, setTitle) = React.useState(_ => "");
  let (body, setBody) = React.useState(_ => "");

  let submitForm = (event: ReactEvent.Form.t) => {
    ReactEvent.Form.preventDefault(event);
    mutate(
      ~variables={
        input: {
          issue: {
            authorId: user.id,
            body,
            status: `OPEN,
            title,
          },
        },
      },
      ~updater=
        (store, _response) => {
          let payload =
            ReasonRelay.RecordSourceSelectorProxy.getRootField(
              store,
              ~fieldName="createIssue",
            );

          let issue =
            switch (payload) {
            | Some(payload) =>
              ReasonRelay.RecordProxy.getLinkedRecord(
                payload,
                ~name="issue",
                (),
              )
            | None => None
            };

          let root = ReasonRelay.RecordSourceSelectorProxy.getRoot(store);

          let issues =
            ReasonRelay.RecordProxy.getLinkedRecords(
              root,
              ~name="issues",
              (),
            );

          let new_issues =
            switch (issues) {
            | Some(issues) => Array.append(issues, [|issue|])
            | None => [|issue|]
            };

          ReasonRelay.RecordProxy.setLinkedRecords(
            root,
            ~name="issues",
            ~records=new_issues,
            (),
          )
          |> ignore;
        },
      (),
    )
    |> ignore;
  };

  <div>
    <CommonHeader />
    <form onSubmit=submitForm>
      <label htmlFor="title"> {React.string("Title:")} </label>
      <input
        id="title"
        type_="text"
        value=title
        onChange={e => {
          let value = ReactEvent.Form.target(e)##value;
          setTitle(value);
        }}
      />
      <label htmlFor="body"> {React.string("Body:")} </label>
      <textarea
        id="body"
        type_="text"
        value=body
        onChange={e => {
          let value = ReactEvent.Form.target(e)##value;
          setBody(value);
        }}
      />
      <button> {React.string("Create issue")} </button>
    </form>
  </div>;
};
