[%raw {|require("./styles/css/create-stream.css")|}];
[%raw {|require("./styles/css/global.css")|}];
[%raw {|require("./styles/css/defaults.css")|}];

open Belt;

let (||||) = (optional, default) => Option.getWithDefault(optional, default);

module AllOrganisations = [%graphql
  {|
query AllOrgs {
  organisations {
    announcement_blog
    country
    cover_image
    description
    id
    logo
    logo_badge
    name
    onboarding_status
    website
    youtube_vid
  }
}
|}
];

[@react.component]
let make = () => {
  let allOrgsQuery = AllOrganisations.use();

  let onClick = (id, _event) => {
    Js.log("clicked the id: " ++ id);
  };

  switch (allOrgsQuery) {
  | {loading: true} => "Loading..."->React.string
  | {error: Some(_error)} =>
    Js.log(_error);
    "Error loading data"->React.string;
  | {data: Some({organisations})} =>
    <table>
      <thead>
        <tr>
          <th> {js| 📁 |js}->React.string " Type"->React.string </th>
          <th>
            {js| 📥 |js}->React.string
            " Skale Endpoint"->React.string
          </th>
          <th>
            {js| 📤 |js}->React.string
            " Arweave Endpoint"->React.string
          </th>
          <th> {js| 🕔 |js}->React.string " Frequency"->React.string </th>
          <th> {js| ⏳ |js}->React.string " Next Sync"->React.string </th>
          <th> {js| 🧮 |js}->React.string " # Syncs"->React.string </th>
          <th> {js| 🏷️ |js}->React.string " Label"->React.string </th>
          <th> {js| 🏗️ |js}->React.string " Actions"->React.string </th>
        </tr>
      </thead>
      <tbody>
        {organisations
         ->Belt.Array.map(
             (
               {
                 announcement_blog,
                 country,
                 cover_image,
                 description,
                 id,
                 logo,
                 logo_badge,
                 name,
                 onboarding_status,
                 website,
                 youtube_vid,
               },
             ) => {
             <tr key=id>

                 <td onClick={onClick(id)}>
                   {(announcement_blog |||| "")->React.string}
                 </td>
                 <td onClick={onClick(id)}>
                   {(country |||| "")->React.string}
                 </td>
                 <td onClick={onClick(id)}>
                   {(cover_image |||| "")->React.string}
                 </td>
                 //  <td onClick={onClick(id)}>
                 //    {(description |||| "")->React.string}
                 //  </td>
                 <td onClick={onClick(id)}> id->React.string </td>
                 <td onClick={onClick(id)}> logo->React.string </td>
                 <td onClick={onClick(id)}>
                   {(logo_badge |||| "")->React.string}
                 </td>
                 <td onClick={onClick(id)}> name->React.string </td>
                 <td onClick={onClick(id)}> website->React.string </td>
                 <td onClick={onClick(id)}>
                   {(youtube_vid |||| "")->React.string}
                 </td>
               </tr>
               //  <td onClick={onClick(id)}>
               //    onboarding_status->React.string
               //  </td>
           })
         ->React.array}
      </tbody>
    </table>
  | _ => React.null
  };
};
