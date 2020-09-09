ReactExperimental.renderConcurrentRootAtElementWithId(
  <ReasonRelay.Context.Provider environment=RelayEnvironment.environment>
    <React.Suspense fallback={React.string("LOADING")}>
      <App />
    </React.Suspense>
  </ReasonRelay.Context.Provider>,
  "root",
);
