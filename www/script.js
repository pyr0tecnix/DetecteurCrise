function sendData() {
  var xhr = getXMLHttpRequest();
  xhr.open('POST', encodeURI('delete'));
  xhr.setRequestHeader('contentType', 'application/json');
  xhr.send("delete");
}


function getData(){
  var xhr = getXMLHttpRequest();
  xhr.open('POST', encodeURI('getdata'));
  xhr.setRequestHeader('contentType', 'application/txt');
  xhr.onload = function(){
    try {
      if(xhr.status == 200) {
        var blob = new Blob([xhr.responseText], {type: "application/txt"});
        var url  = URL.createObjectURL(blob);
        var link = document.createElement("a");
        link.setAttribute("href", url);
        link.setAttribute("download", slugify("Detecteur_" + new Date().toDateString()));
        document.body.appendChild(link); // Required for FF
        link.click();
      }
    }
    catch(error) {
      console.log("Erreur de réception des données : " + error);
    }
  };
  xhr.send("getdata");
}

/*Fonction d'instanciation de l'objet XMLHttpRequest*/
function getXMLHttpRequest() {
  console.log("STACK - getXMLHttpRequest");
  var xhr = null;

  if (window.XMLHttpRequest || window.ActiveXObject) {
    if (window.ActiveXObject) {
      try {
        xhr = new ActiveXObject("Msxml2.XMLHTTP");
      } catch(e) {
        xhr = new ActiveXObject("Microsoft.XMLHTTP");
      }
    } else {
      xhr = new XMLHttpRequest();
    }
  } else {
    alert("Votre navigateur ne supporte pas l'objet XMLHTTPRequest...");
    return null;
  }

  return xhr;
}

function slugify(text)
{
  if (text == "") {
    text = "defaut";
  }
  return text.toString().toLowerCase()
  .replace(/\s+/g, '-')
  .replace(/\-\-+/g, '-')
  .replace(/^-+/, '')
  .replace(/-+$/, '')
  .replace(/[ÀÁÂÃÄÅ]/g,"A")
  .replace(/[àáâãäå]/g,"a")
  .replace(/[ÈÉÊË]/g,"E")
  .replace(/[éêèë]/g,"e")
  .replace(/[ÏÎ]/g,"I")
  .replace(/[îï]/g,"i");
}
