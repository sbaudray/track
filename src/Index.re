ReactExperimental.renderConcurrentRootAtElementWithId(
  <ReasonRelay.Context.Provider environment=RelayEnvironment.environment>
    <React.Suspense fallback={React.string("LOADING")}>
      <UserProvider> <App /> </UserProvider>
    </React.Suspense>
  </ReasonRelay.Context.Provider>,
  "root",
);
