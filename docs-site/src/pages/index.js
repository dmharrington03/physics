import * as React from "react";
import { graphql } from "gatsby";

import Seo from "../components/seo";
import TitleBar from "../components/titlebar";
import ArticleCard from "../components/article-card";

const BlogIndex = ({ data, location }) => {
  const siteTitle = data.site.siteMetadata?.title || `Title`;
  const posts = data.allMarkdownRemark.nodes;
  const images = data.allFile.nodes;

  if (posts.length === 0) {
    return (
      <div>
        <Seo title="All posts" />
        <p>
          No blog posts found. Check back again later!
        </p>
      </div>
    );
  }

  return (
    <div>
      <Seo title="Computational Physics" />
      <TitleBar />
      <div className="uk-container uk-margin-top">
        <div className="uk-grid uk-grid-match" data-uk-grid 
          data-uk-height-match="target: > div > div > a > div.uk-card-body">
          {posts.map((post) => {
            const title = post.frontmatter.title || post.fields.slug;
            const imgMatch = images.find((node) => post.frontmatter.title === node.name);
            return (
              <div className="uk-width-1-3@m uk-width-1-2@s">
                <ArticleCard title={title} 
                  to={post.fields.slug.replace(/\s+/g, '')} 
                  imgURL={ imgMatch ? imgMatch.publicURL : "" }
                  tag={posts.indexOf(post) === 0 ? "New!" : ""}
                  date={post.frontmatter.date}
                />
              </div>
            );
          })}
        </div>
      </div>
      <footer className="uk-height-small">
    
      </footer>
    </div>
  );
};

export default BlogIndex;

export const pageQuery = graphql`
  query {
    site {
      siteMetadata {
        title
      }
    }
    allMarkdownRemark(sort: { fields: [frontmatter___date], order: DESC }) {
      nodes {
        excerpt
        fields {
          slug
        }
        frontmatter {
          date(formatString: "MMMM DD, YYYY")
          title
          description
        }
      }
    }
    allFile(filter: {relativeDirectory: {eq: "header-images"}}) {
      nodes {
        publicURL
        name
      }
    }
  }
`;
