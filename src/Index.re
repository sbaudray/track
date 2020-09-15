Module.require("./Index.css");

ReactExperimental.renderConcurrentRootAtElementWithId(
  <ReasonRelay.Context.Provider environment=RelayEnvironment.environment>
    <ReasonReactErrorBoundary
      fallback={_ => <div> {React.string("Oops")} </div>}>
      <React.Suspense fallback={React.string("LOADING")}>
        <User.Provider> <App /> </User.Provider>
      </React.Suspense>
    </ReasonReactErrorBoundary>
  </ReasonRelay.Context.Provider>,
  "root",
);
