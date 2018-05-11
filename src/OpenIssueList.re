/* Create a GraphQL Query by using the graphql_ppx */
module GetOpenIssues = [%graphql
  {|
    query {
      repository(owner: "facebook", name: "reason") {
        issues(first: 100, states: OPEN, orderBy: {field: UPDATED_AT, direction: DESC}) {
          totalCount
          nodes {
            title
            updatedAt
          }
        }
      }
    }
|}
];

module GetOpenIssuesQuery = ReasonApollo.CreateQuery(GetOpenIssues);

let component = ReasonReact.statelessComponent("OpenIssueList");

let make = _children => {
  ...component,
  render: (_) => {
    let reposQuery = GetOpenIssues.make();
    <GetOpenIssuesQuery variables=reposQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | NoData => <div> (ReasonReact.string("No Data")) </div>
             | Loading => <div> (ReasonReact.string("Loading")) </div>
             | Error(_) => <div> (ReasonReact.string("ERROR")) </div>
             | Data(response) =>
               switch (response##repository) {
               | None => <div> (ReasonReact.string("Repository does not exist")) </div>
               | Some(repository) =>
                  <div>
                    (ReasonReact.string(string_of_int(repository##issues##totalCount) ++ " open issues."))
                    (switch (repository##issues##nodes) {
                    | None => <div> (ReasonReact.string("No issues")) </div>
                    | Some(nodes) =>
                      ReasonReact.array(
                        Array.map(
                          node =>
                            switch(node) {
                            | None => <div> (ReasonReact.string("Waht?")) </div>
                            | Some(node) => <div> (ReasonReact.string(node##title ++ " - ")) </div>
                            },
                        nodes)
                      )
                    })
                  </div>
               }
             }
         )
    </GetOpenIssuesQuery>;
  },
};
