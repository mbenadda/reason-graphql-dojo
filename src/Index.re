/*
  Enhance your application with the `ReasonApollo.Provider`
  passing it your client instance
*/
ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client=Client.instance>
      <h1> (ReasonReact.string("Goals 2+3")) </h1>
      <RepositoryList />
      <h1> (ReasonReact.string("Goal 4")) </h1>
      <OpenIssueList />
  </ReasonApollo.Provider>
, "index");
