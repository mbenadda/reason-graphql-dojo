/* Create a GraphQL Query by using the graphql_ppx */
module GetRepos = [%graphql
  {|
    query {
      viewer {
        repositories(first: 20, orderBy: {field: STARGAZERS, direction: DESC}) {
          nodes {
            name
            stargazers {
              totalCount
            }
            viewerHasStarred
          }
        }
      }
    }
|}
];

module GetReposQuery = ReasonApollo.CreateQuery(GetRepos);

let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: (_) => {
    let reposQuery = GetRepos.make();
    <GetReposQuery variables=reposQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | NoData => <div> (ReasonReact.string("No Data")) </div>
             | Loading => <div> (ReasonReact.string("Loading")) </div>
             | Error(_) => <div> (ReasonReact.string("ERROR")) </div>
             | Data(response) =>
               switch (response##viewer##repositories##nodes) {
               | None => <div> (ReasonReact.string("No repositories")) </div>
               | Some(nodes) =>
                 ReasonReact.array(
                   Array.map(
                     node =>
                       switch (node) {
                       | None => <div> (ReasonReact.string("Waht?")) </div>
                       | Some(node) =>
                         let star = switch (node##viewerHasStarred) {
                         | true => {js|⭐️ |js}
                         | false => {js|★ |js}
                         };
                         <div>
                           (
                             ReasonReact.string(
                               star
                               ++ node##name
                               ++ ": "
                               ++ string_of_int(node##stargazers##totalCount),
                             )
                           )
                         </div>
                       },
                     nodes,
                   ),
                 )
               }
             }
         )
    </GetReposQuery>;
  },
};
