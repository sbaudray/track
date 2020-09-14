Module.require("./Index.css");

ReactExperimental.renderConcurrentRootAtElementWithId(
  <ReasonRelay.Context.Provider environment=RelayEnvironment.environment>
    <React.Suspense fallback={React.string("LOADING")}>
      <User.Provider> <App /> </User.Provider>
    </React.Suspense>
  </ReasonRelay.Context.Provider>,
  "root",
);
