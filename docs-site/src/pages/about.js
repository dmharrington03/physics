import * as React from "react";
import { graphql } from "gatsby";

import Seo from "../components/seo";
import TitleBar from "../components/titlebar";
import PageFooter from "../components/page-footer";
import UIkit from "uikit";
import Icons from 'uikit/dist/js/uikit-icons';


const About = ({ data, location }) => {

  const siteTitle = data.site.siteMetadata?.title || `Title`;
  UIkit.use(Icons);

  return (
    <div>
      <Seo title="Computational Physics" />
      <TitleBar />
      <h1>Hello world</h1>
      <div className="uk-margin">
        <div className="uk-container">Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Urna et pharetra pharetra massa massa ultricies mi. Mollis aliquam ut porttitor leo a diam. Feugiat in ante metus dictum at tempor commodo ullamcorper a. Leo integer malesuada nunc vel risus commodo viverra maecenas. Pulvinar sapien et ligula ullamcorper malesuada proin. Et magnis dis parturient montes nascetur. Vel pretium lectus quam id. Posuere sollicitudin aliquam ultrices sagittis orci. Nisi scelerisque eu ultrices vitae auctor eu. Et malesuada fames ac turpis egestas integer eget. Mauris a diam maecenas sed enim ut sem viverra aliquet. Bibendum at varius vel pharetra vel. Enim nulla aliquet porttitor lacus luctus. Consectetur adipiscing elit pellentesque habitant morbi tristique senectus. Vestibulum sed arcu non odio euismod lacinia at.

Dui accumsan sit amet nulla. Iaculis eu non diam phasellus vestibulum. Dui sapien eget mi proin sed libero enim. Mauris cursus mattis molestie a iaculis at. Senectus et netus et malesuada fames. Est velit egestas dui id. Pretium viverra suspendisse potenti nullam ac tortor. Non odio euismod lacinia at quis risus sed vulputate odio. Non nisi est sit amet facilisis magna. Elementum sagittis vitae et leo duis ut. Sem integer vitae justo eget magna fermentum iaculis eu. Facilisi cras fermentum odio eu feugiat pretium nibh ipsum. Aliquet bibendum enim facilisis gravida neque convallis. Libero justo laoreet sit amet cursus sit amet.

Et malesuada fames ac turpis egestas integer eget aliquet. Enim diam vulputate ut pharetra sit amet aliquam id diam. Sapien et ligula ullamcorper malesuada proin libero nunc consequat. Elit scelerisque mauris pellentesque pulvinar. Faucibus in ornare quam viverra orci sagittis eu volutpat. Egestas sed sed risus pretium quam vulputate dignissim. Scelerisque fermentum dui faucibus in ornare quam. Nisl rhoncus mattis rhoncus urna. Praesent semper feugiat nibh sed. Gravida cum sociis natoque penatibus et magnis dis parturient montes. Facilisi morbi tempus iaculis urna. Tristique senectus et netus et malesuada fames ac. Tortor condimentum lacinia quis vel eros. Nisl pretium fusce id velit ut tortor pretium viverra. Posuere morbi leo urna molestie at elementum eu facilisis sed. Faucibus interdum posuere lorem ipsum dolor sit amet consectetur adipiscing.

Cras pulvinar mattis nunc sed blandit libero volutpat sed. In hac habitasse platea dictumst quisque sagittis purus. Est sit amet facilisis magna etiam tempor orci. In iaculis nunc sed augue lacus. Et magnis dis parturient montes. A diam sollicitudin tempor id. Hendrerit dolor magna eget est lorem ipsum dolor sit. Diam ut venenatis tellus in metus vulputate eu scelerisque felis. Lacus vel facilisis volutpat est velit egestas. Amet mauris commodo quis imperdiet massa tincidunt. Parturient montes nascetur ridiculus mus mauris vitae. Justo nec ultrices dui sapien eget mi proin sed libero. Tincidunt eget nullam non nisi est sit amet facilisis magna.

Vitae auctor eu augue ut lectus. Mattis nunc sed blandit libero volutpat. In mollis nunc sed id semper. Pretium lectus quam id leo in vitae turpis massa. Nibh mauris cursus mattis molestie a iaculis at erat pellentesque. Non enim praesent elementum facilisis leo vel fringilla. Nisl purus in mollis nunc sed. Egestas fringilla phasellus faucibus scelerisque eleifend donec pretium vulputate. Integer enim neque volutpat ac tincidunt vitae. Aliquet nibh praesent tristique magna. A pellentesque sit amet porttitor. Egestas integer eget aliquet nibh praesent tristique magna. Nisl purus in mollis nunc sed id semper risus. Fames ac turpis egestas maecenas pharetra convallis posuere. Aliquet porttitor lacus luctus accumsan tortor posuere. Odio eu feugiat pretium nibh ipsum consequat. Convallis convallis tellus id interdum velit laoreet id donec ultrices. Nulla facilisi nullam vehicula ipsum. Proin nibh nisl condimentum id venenatis a. Integer quis auctor elit sed vulputate mi.s</div>
      </div>

      {/*//TODO  write about section*/}

      <PageFooter />
      
    </div>
  );
};

export default About;

export const pageQuery = graphql`
  query {
    site {
      siteMetadata {
        title
      }
    }
  }
`;