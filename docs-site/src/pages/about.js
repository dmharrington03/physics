import * as React from "react";
import { graphql } from "gatsby";

import Seo from "../components/seo";
import TitleBar from "../components/titlebar";
import PageFooter from "../components/page-footer";
import UIkit from "uikit";
import Icons from 'uikit/dist/js/uikit-icons';


const About = ({ data, location }) => {

  const portraitURL = data.allFile.edges[0].node.publicURL;
  const codebgURL = data.allFile.edges[1].node.publicURL;

  UIkit.use(Icons);

  const bgPortraitStyle = {
    backgroundImage: `url(${portraitURL})`
  }

  const bgPortraitStyleSmall = {
    backgroundImage: `url(${portraitURL})`,
    backgroundColor: "#333333"
  }

  const bgMainStyle = {
    backgroundImage: `url(${codebgURL})`,
    backgroundColor: "#222222"
  }


  return (
    <div>
      <Seo title="Computational Physics" />
      <TitleBar />
      <div className="uk-flex uk-flex-center uk-grid">
          <div className="uk-width-expand uk-width-1-2@m uk-flex uk-flex-center uk-flex-middle uk-padding uk-visible@m">
            <div className="uk-width-1-2@m uk-width-2-3">
              <h1 className="uk-text-center uk-text-left@s">About Me</h1>
              <p>My name is Daniel Harrington. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>
            </div>
          </div>
          <div className="uk-width-expand uk-flex uk-flex-center uk-background-cover 
          uk-background-top-left uk-background-fixed uk-background-blend-soft-light uk-hidden@m uk-light" style={ bgPortraitStyleSmall }>
            <div className="uk-padding">
              <h1 className="uk-text-center uk-margin-top">About Me</h1>
              <div className="uk-container">
                <p>My name is Daniel Harrington. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>
              </div>
            </div>
          </div>
          <div className="uk-width-1-2@m uk-visible@s uk-background-image@m uk-background-cover uk-background-top-left" style={ bgPortraitStyle }></div>
      </div>
      <div className="uk-flex uk-flex-center
        uk-background-cover uk-background-blend-soft-light uk-light" style={ bgMainStyle }>
        <div className="uk-padding">
          <h1 className="uk-margin-top uk-text-center">About the Project</h1>
          <div className="uk-container">
            <h2>Format</h2>
            <p>For each topic of physics investigated, there are one or several programs demonstrating the corresponding theory through visualizations or simulations.</p>
            
            <p>Programs are written in C++ using the SFML framework. Though Python is often a popular choice for scientific uses, I chose C++ due its comparative speed and popularity in computer graphics. The main advantage of Python is the large amount of abstraction it offers both for mathematical and scientific computations, but since the goal of this project is to develop these tools from scratch, this is not an influential factor.</p>
            
            <h2>Topics</h2>
            <p>Through this project, I aim to cover principles of physics presented in a calculus-based introductory physics course, as well as anything else that happens to interest me. Although the structure is not organized around any particular curriculum, material is loosely borrowed from MIT's 8.01 course and Leonard Susskind's Classical Mechanics Stanford lectures from The Theoretical Minumum courses. Knowledge of basic calculus and programming principles are assumed in communication of concepts.</p>
            
            <h2>Download</h2>
            <p>If you wish to try any of the programs or build upon them, SFML must be installed on your platform.</p>
          </div>
        </div>
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
    allFile(filter: {name: {in: ["portrait", "codebg"]}}) {
      edges {
        node {
          publicURL
        }
      }
    }
  }
`;